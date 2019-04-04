# frozen_string_literal: true

require 'spec_helper'
require 'util/class_decorations'

RSpec.describe Util::ClassDecorations do
  DescribedClass = described_class

  let(:decorated) do
    Class.new do
      extend DescribedClass

      # It's ok to :reek:UtilityFunction
      def f_impl(x) # rubocop:disable Naming/UncommunicativeMethodParamName
        x + 1
      end

      func def f(x) # rubocop:disable Naming/UncommunicativeMethodParamName
        f_impl x
      end
    end
  end

  it 'can be extended' do
    expect { decorated }.not_to raise_error
  end

  describe 'func decorator' do
    let(:instance) { decorated.new }
    let(:value) { 12 }

    it 'allows methods to be called argless and return a proc' do
      expect(instance.f.call(value)).to eq instance.f_impl(value)
    end

    it 'propagates arguments each time' do
      expect(instance.f.call(value)).to eq instance.f_impl(value)
      expect(instance.f.call(value + 1)).to eq instance.f_impl(value + 1)
    end

    it 'allows methods to be called normally also' do
      expect(instance.f(value)).to eq instance.f_impl(value)
    end
  end
end
