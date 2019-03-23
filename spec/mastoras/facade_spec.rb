# frozen_string_literal: true

require 'spec_helper'

require 'mastoras/facade'

RSpec.describe Mastoras::Facade do
  let(:samples) { Pathname.new(__dir__) / '..' / '..' / '_sample' }
  let(:sample_good) { samples / 'good' / 'mastrofile' }
  let(:facade) { described_class.new sample_good }
  it 'exists' do
  end

  describe '#initialize' do
    describe 'with good mastroroot' do
      subject { facade }
      it 'gets constructed' do
        expect { subject }.not_to raise_error
      end

      describe '#ws (workspace)' do
        describe '#config' do
          subject { facade.ws.config }
          it { is_expected.to be_a Hash }
        end
        describe '#mastrorepo' do
          subject { facade.ws.mastrorepo }
          it { is_expected.to be_a Pathname }
          it 'is a child of mastroroot' do
            expect(sample_good.dirname.children).to include subject
          end
          describe '#basename' do
            subject { facade.ws.mastrorepo.basename.to_s }
            it { is_expected.to eq 'mastrorepo' }
          end
        end
        describe '#scrolls.name' do
          subject { facade.ws.scrolls.map(&:name) }
          describe 'values' do
            it 'includes arch_base' do
              expect subject.include? 'arch_base'
            end
            it 'includes arch_updated' do
              expect subject.include? 'arch_updated'
            end
          end
        end
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
