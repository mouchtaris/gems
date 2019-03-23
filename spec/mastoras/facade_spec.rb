# frozen_string_literal: true

require 'spec_helper'

require 'mastoras/facade'

RSpec.describe Mastoras::Facade do
  let(:samples) { Pathname.new(__dir__) / '..' / '..' / '_sample' }
  let(:sample_good) { samples / 'good' }
  it 'exists' do
  end

  describe '#initialize' do
    describe 'with good mastroroot' do
      subject { described_class.new sample_good }
      it 'gets constructed' do
        expect { subject }.not_to raise_error
      end
    end

    describe 'with wrong arguments' do
      subject { described_class.new sample_good.to_s }
      it 'does not accept non-Pathname root' do
        expect { subject }.to raise_error ArgumentError
      end
    end
  end
end
