# frozen_string_literal: true

require 'spec_helper'
require 'util/tap'

RSpec.describe Util::Tap do
  let(:block_spy) do
    instance_double(Proc).tap do |spy|
      allow(spy).to receive(:call)
    end
  end
  let(:block) { ->(obj) { block_spy.call(obj) } }
  let(:obj) { instance_double(Object) }
  let(:tap) { described_class.new(&block) }

  describe 'construction' do
    context 'without a block' do
      let(:block) { nil }
      it 'fails immediately' do
        expect { tap }.to raise_error LocalJumpError
      end
    end
  end

  describe 'behaviour' do
    after { tap.call(obj) }

    it 'calls #tap() on the given object' do
      expect(obj).to receive(:tap).with(no_args)
    end

    it 'calls the block given in construction with the object' do
      expect(block_spy).to receive(:call).with(obj)
    end
  end
end
